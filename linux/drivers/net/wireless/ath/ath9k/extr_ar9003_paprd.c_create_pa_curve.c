#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  y_est ;
typedef  int /*<<< orphan*/  x_tilde ;
typedef  int /*<<< orphan*/  x_est ;
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  theta ;
typedef  unsigned int s32 ;
typedef  int /*<<< orphan*/  Y ;

/* Variables and functions */
 int NUM_BIN ; 
 int PAPRD_TABLE_SZ ; 
 unsigned int abs (int) ; 
 int /*<<< orphan*/  find_expn (unsigned int) ; 
 int find_proper_scale (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool create_pa_curve(u32 *data_L, u32 *data_U, u32 *pa_table, u16 *gain)
{
	unsigned int thresh_accum_cnt;
	int x_est[NUM_BIN + 1], Y[NUM_BIN + 1], theta[NUM_BIN + 1];
	int PA_in[NUM_BIN + 1];
	int B1_tmp[NUM_BIN + 1], B2_tmp[NUM_BIN + 1];
	unsigned int B1_abs_max, B2_abs_max;
	int max_index, scale_factor;
	int y_est[NUM_BIN + 1];
	int x_est_fxp1_nonlin, x_tilde[NUM_BIN + 1];
	unsigned int x_tilde_abs;
	int G_fxp, Y_intercept, order_x_by_y, M, I, L, sum_y_sqr, sum_y_quad;
	int Q_x, Q_B1, Q_B2, beta_raw, alpha_raw, scale_B;
	int Q_scale_B, Q_beta, Q_alpha, alpha, beta, order_1, order_2;
	int order1_5x, order2_3x, order1_5x_rem, order2_3x_rem;
	int y5, y3, tmp;
	int theta_low_bin = 0;
	int i;

	/* disregard any bin that contains <= 16 samples */
	thresh_accum_cnt = 16;
	scale_factor = 5;
	max_index = 0;
	memset(theta, 0, sizeof(theta));
	memset(x_est, 0, sizeof(x_est));
	memset(Y, 0, sizeof(Y));
	memset(y_est, 0, sizeof(y_est));
	memset(x_tilde, 0, sizeof(x_tilde));

	for (i = 0; i < NUM_BIN; i++) {
		s32 accum_cnt, accum_tx, accum_rx, accum_ang;

		/* number of samples */
		accum_cnt = data_L[i] & 0xffff;

		if (accum_cnt <= thresh_accum_cnt)
			continue;

		max_index++;

		/* sum(tx amplitude) */
		accum_tx = ((data_L[i] >> 16) & 0xffff) |
		    ((data_U[i] & 0x7ff) << 16);

		/* sum(rx amplitude distance to lower bin edge) */
		accum_rx = ((data_U[i] >> 11) & 0x1f) |
		    ((data_L[i + 23] & 0xffff) << 5);

		/* sum(angles) */
		accum_ang = ((data_L[i + 23] >> 16) & 0xffff) |
		    ((data_U[i + 23] & 0x7ff) << 16);

		accum_tx <<= scale_factor;
		accum_rx <<= scale_factor;
		x_est[max_index] =
			(((accum_tx + accum_cnt) / accum_cnt) + 32) >>
			scale_factor;

		Y[max_index] =
			((((accum_rx + accum_cnt) / accum_cnt) + 32) >>
			    scale_factor) +
			(1 << scale_factor) * i + 16;

		if (accum_ang >= (1 << 26))
			accum_ang -= 1 << 27;

		theta[max_index] =
			((accum_ang * (1 << scale_factor)) + accum_cnt) /
			accum_cnt;
	}

	/*
	 * Find average theta of first 5 bin and all of those to same value.
	 * Curve is linear at that range.
	 */
	for (i = 1; i < 6; i++)
		theta_low_bin += theta[i];

	theta_low_bin = theta_low_bin / 5;
	for (i = 1; i < 6; i++)
		theta[i] = theta_low_bin;

	/* Set values at origin */
	theta[0] = theta_low_bin;
	for (i = 0; i <= max_index; i++)
		theta[i] -= theta_low_bin;

	x_est[0] = 0;
	Y[0] = 0;
	scale_factor = 8;

	/* low signal gain */
	if (x_est[6] == x_est[3])
		return false;

	G_fxp =
	    (((Y[6] - Y[3]) * 1 << scale_factor) +
	     (x_est[6] - x_est[3])) / (x_est[6] - x_est[3]);

	/* prevent division by zero */
	if (G_fxp == 0)
		return false;

	Y_intercept =
	    (G_fxp * (x_est[0] - x_est[3]) +
	     (1 << scale_factor)) / (1 << scale_factor) + Y[3];

	for (i = 0; i <= max_index; i++)
		y_est[i] = Y[i] - Y_intercept;

	for (i = 0; i <= 3; i++) {
		y_est[i] = i * 32;
		x_est[i] = ((y_est[i] * 1 << scale_factor) + G_fxp) / G_fxp;
	}

	if (y_est[max_index] == 0)
		return false;

	x_est_fxp1_nonlin =
	    x_est[max_index] - ((1 << scale_factor) * y_est[max_index] +
				G_fxp) / G_fxp;

	order_x_by_y =
	    (x_est_fxp1_nonlin + y_est[max_index]) / y_est[max_index];

	if (order_x_by_y == 0)
		M = 10;
	else if (order_x_by_y == 1)
		M = 9;
	else
		M = 8;

	I = (max_index > 15) ? 7 : max_index >> 1;
	L = max_index - I;
	scale_factor = 8;
	sum_y_sqr = 0;
	sum_y_quad = 0;
	x_tilde_abs = 0;

	for (i = 0; i <= L; i++) {
		unsigned int y_sqr;
		unsigned int y_quad;
		unsigned int tmp_abs;

		/* prevent division by zero */
		if (y_est[i + I] == 0)
			return false;

		x_est_fxp1_nonlin =
		    x_est[i + I] - ((1 << scale_factor) * y_est[i + I] +
				    G_fxp) / G_fxp;

		x_tilde[i] =
		    (x_est_fxp1_nonlin * (1 << M) + y_est[i + I]) / y_est[i +
									  I];
		x_tilde[i] =
		    (x_tilde[i] * (1 << M) + y_est[i + I]) / y_est[i + I];
		x_tilde[i] =
		    (x_tilde[i] * (1 << M) + y_est[i + I]) / y_est[i + I];
		y_sqr =
		    (y_est[i + I] * y_est[i + I] +
		     (scale_factor * scale_factor)) / (scale_factor *
						       scale_factor);
		tmp_abs = abs(x_tilde[i]);
		if (tmp_abs > x_tilde_abs)
			x_tilde_abs = tmp_abs;

		y_quad = y_sqr * y_sqr;
		sum_y_sqr = sum_y_sqr + y_sqr;
		sum_y_quad = sum_y_quad + y_quad;
		B1_tmp[i] = y_sqr * (L + 1);
		B2_tmp[i] = y_sqr;
	}

	B1_abs_max = 0;
	B2_abs_max = 0;
	for (i = 0; i <= L; i++) {
		int abs_val;

		B1_tmp[i] -= sum_y_sqr;
		B2_tmp[i] = sum_y_quad - sum_y_sqr * B2_tmp[i];

		abs_val = abs(B1_tmp[i]);
		if (abs_val > B1_abs_max)
			B1_abs_max = abs_val;

		abs_val = abs(B2_tmp[i]);
		if (abs_val > B2_abs_max)
			B2_abs_max = abs_val;
	}

	Q_x = find_proper_scale(find_expn(x_tilde_abs), 10);
	Q_B1 = find_proper_scale(find_expn(B1_abs_max), 10);
	Q_B2 = find_proper_scale(find_expn(B2_abs_max), 10);

	beta_raw = 0;
	alpha_raw = 0;
	for (i = 0; i <= L; i++) {
		x_tilde[i] = x_tilde[i] / (1 << Q_x);
		B1_tmp[i] = B1_tmp[i] / (1 << Q_B1);
		B2_tmp[i] = B2_tmp[i] / (1 << Q_B2);
		beta_raw = beta_raw + B1_tmp[i] * x_tilde[i];
		alpha_raw = alpha_raw + B2_tmp[i] * x_tilde[i];
	}

	scale_B =
	    ((sum_y_quad / scale_factor) * (L + 1) -
	     (sum_y_sqr / scale_factor) * sum_y_sqr) * scale_factor;

	Q_scale_B = find_proper_scale(find_expn(abs(scale_B)), 10);
	scale_B = scale_B / (1 << Q_scale_B);
	if (scale_B == 0)
		return false;
	Q_beta = find_proper_scale(find_expn(abs(beta_raw)), 10);
	Q_alpha = find_proper_scale(find_expn(abs(alpha_raw)), 10);
	beta_raw = beta_raw / (1 << Q_beta);
	alpha_raw = alpha_raw / (1 << Q_alpha);
	alpha = (alpha_raw << 10) / scale_B;
	beta = (beta_raw << 10) / scale_B;
	order_1 = 3 * M - Q_x - Q_B1 - Q_beta + 10 + Q_scale_B;
	order_2 = 3 * M - Q_x - Q_B2 - Q_alpha + 10 + Q_scale_B;
	order1_5x = order_1 / 5;
	order2_3x = order_2 / 3;
	order1_5x_rem = order_1 - 5 * order1_5x;
	order2_3x_rem = order_2 - 3 * order2_3x;

	for (i = 0; i < PAPRD_TABLE_SZ; i++) {
		tmp = i * 32;
		y5 = ((beta * tmp) >> 6) >> order1_5x;
		y5 = (y5 * tmp) >> order1_5x;
		y5 = (y5 * tmp) >> order1_5x;
		y5 = (y5 * tmp) >> order1_5x;
		y5 = (y5 * tmp) >> order1_5x;
		y5 = y5 >> order1_5x_rem;
		y3 = (alpha * tmp) >> order2_3x;
		y3 = (y3 * tmp) >> order2_3x;
		y3 = (y3 * tmp) >> order2_3x;
		y3 = y3 >> order2_3x_rem;
		PA_in[i] = y5 + y3 + (256 * tmp) / G_fxp;

		if (i >= 2) {
			tmp = PA_in[i] - PA_in[i - 1];
			if (tmp < 0)
				PA_in[i] =
				    PA_in[i - 1] + (PA_in[i - 1] -
						    PA_in[i - 2]);
		}

		PA_in[i] = (PA_in[i] < 1400) ? PA_in[i] : 1400;
	}

	beta_raw = 0;
	alpha_raw = 0;

	for (i = 0; i <= L; i++) {
		int theta_tilde =
		    ((theta[i + I] << M) + y_est[i + I]) / y_est[i + I];
		theta_tilde =
		    ((theta_tilde << M) + y_est[i + I]) / y_est[i + I];
		theta_tilde =
		    ((theta_tilde << M) + y_est[i + I]) / y_est[i + I];
		beta_raw = beta_raw + B1_tmp[i] * theta_tilde;
		alpha_raw = alpha_raw + B2_tmp[i] * theta_tilde;
	}

	Q_beta = find_proper_scale(find_expn(abs(beta_raw)), 10);
	Q_alpha = find_proper_scale(find_expn(abs(alpha_raw)), 10);
	beta_raw = beta_raw / (1 << Q_beta);
	alpha_raw = alpha_raw / (1 << Q_alpha);

	alpha = (alpha_raw << 10) / scale_B;
	beta = (beta_raw << 10) / scale_B;
	order_1 = 3 * M - Q_x - Q_B1 - Q_beta + 10 + Q_scale_B + 5;
	order_2 = 3 * M - Q_x - Q_B2 - Q_alpha + 10 + Q_scale_B + 5;
	order1_5x = order_1 / 5;
	order2_3x = order_2 / 3;
	order1_5x_rem = order_1 - 5 * order1_5x;
	order2_3x_rem = order_2 - 3 * order2_3x;

	for (i = 0; i < PAPRD_TABLE_SZ; i++) {
		int PA_angle;

		/* pa_table[4] is calculated from PA_angle for i=5 */
		if (i == 4)
			continue;

		tmp = i * 32;
		if (beta > 0)
			y5 = (((beta * tmp - 64) >> 6) -
			      (1 << order1_5x)) / (1 << order1_5x);
		else
			y5 = ((((beta * tmp - 64) >> 6) +
			       (1 << order1_5x)) / (1 << order1_5x));

		y5 = (y5 * tmp) / (1 << order1_5x);
		y5 = (y5 * tmp) / (1 << order1_5x);
		y5 = (y5 * tmp) / (1 << order1_5x);
		y5 = (y5 * tmp) / (1 << order1_5x);
		y5 = y5 / (1 << order1_5x_rem);

		if (beta > 0)
			y3 = (alpha * tmp -
			      (1 << order2_3x)) / (1 << order2_3x);
		else
			y3 = (alpha * tmp +
			      (1 << order2_3x)) / (1 << order2_3x);
		y3 = (y3 * tmp) / (1 << order2_3x);
		y3 = (y3 * tmp) / (1 << order2_3x);
		y3 = y3 / (1 << order2_3x_rem);

		if (i < 4) {
			PA_angle = 0;
		} else {
			PA_angle = y5 + y3;
			if (PA_angle < -150)
				PA_angle = -150;
			else if (PA_angle > 150)
				PA_angle = 150;
		}

		pa_table[i] = ((PA_in[i] & 0x7ff) << 11) + (PA_angle & 0x7ff);
		if (i == 5) {
			PA_angle = (PA_angle + 2) >> 1;
			pa_table[i - 1] = ((PA_in[i - 1] & 0x7ff) << 11) +
			    (PA_angle & 0x7ff);
		}
	}

	*gain = G_fxp;
	return true;
}