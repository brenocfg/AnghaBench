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
typedef  int dword ;

/* Variables and functions */
 scalar_t__ CAPIDTMF_RECV_FUNDAMENTAL_DECREMENT ; 
 int CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT ; 

__attribute__((used)) static void capidtmf_goertzel_loop(long *buffer, long *coeffs, short *sample, long count)
{
	int i, j;
	long c, d, q0, q1, q2;

	for (i = 0; i < CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT - 1; i++)
	{
		q1 = buffer[i];
		q2 = buffer[i + CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT];
		d = coeffs[i] >> 1;
		c = d << 1;
		if (c >= 0)
		{
			for (j = 0; j < count; j++)
			{
				q0 = sample[j] - q2 + (c * (q1 >> 16)) + (((dword)(((dword) d) * ((dword)(q1 & 0xffff)))) >> 15);
				q2 = q1;
				q1 = q0;
			}
		}
		else
		{
			c = -c;
			d = -d;
			for (j = 0; j < count; j++)
			{
				q0 = sample[j] - q2 - ((c * (q1 >> 16)) + (((dword)(((dword) d) * ((dword)(q1 & 0xffff)))) >> 15));
				q2 = q1;
				q1 = q0;
			}
		}
		buffer[i] = q1;
		buffer[i + CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT] = q2;
	}
	q1 = buffer[i];
	q2 = buffer[i + CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT];
	c = (coeffs[i] >> 1) << 1;
	if (c >= 0)
	{
		for (j = 0; j < count; j++)
		{
			q0 = sample[j] - q2 + (c * (q1 >> 16)) + (((dword)(((dword)(c >> 1)) * ((dword)(q1 & 0xffff)))) >> 15);
			q2 = q1;
			q1 = q0;
			c -= CAPIDTMF_RECV_FUNDAMENTAL_DECREMENT;
		}
	}
	else
	{
		c = -c;
		for (j = 0; j < count; j++)
		{
			q0 = sample[j] - q2 - ((c * (q1 >> 16)) + (((dword)(((dword)(c >> 1)) * ((dword)(q1 & 0xffff)))) >> 15));
			q2 = q1;
			q1 = q0;
			c += CAPIDTMF_RECV_FUNDAMENTAL_DECREMENT;
		}
	}
	coeffs[i] = c;
	buffer[i] = q1;
	buffer[i + CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT] = q2;
}