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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  coef_lut_a_legacy ; 
 int /*<<< orphan*/  coef_lut_b ; 
 int /*<<< orphan*/  coef_lut_c_c_legacy ; 
 int /*<<< orphan*/  coef_lut_c_y_legacy ; 
 int /*<<< orphan*/  coef_lut_d_c_legacy ; 
 int /*<<< orphan*/  coef_lut_d_y_legacy ; 
 int /*<<< orphan*/  coef_lut_e_c_legacy ; 
 int /*<<< orphan*/  coef_lut_e_y_legacy ; 
 int /*<<< orphan*/  coef_lut_f_c_legacy ; 
 int /*<<< orphan*/  coef_lut_f_y_legacy ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char *hqvdp_dbg_get_lut(u32 *coef)
{
	if (!memcmp(coef, coef_lut_a_legacy, 16))
		return "LUT A";
	if (!memcmp(coef, coef_lut_b, 16))
		return "LUT B";
	if (!memcmp(coef, coef_lut_c_y_legacy, 16))
		return "LUT C Y";
	if (!memcmp(coef, coef_lut_c_c_legacy, 16))
		return "LUT C C";
	if (!memcmp(coef, coef_lut_d_y_legacy, 16))
		return "LUT D Y";
	if (!memcmp(coef, coef_lut_d_c_legacy, 16))
		return "LUT D C";
	if (!memcmp(coef, coef_lut_e_y_legacy, 16))
		return "LUT E Y";
	if (!memcmp(coef, coef_lut_e_c_legacy, 16))
		return "LUT E C";
	if (!memcmp(coef, coef_lut_f_y_legacy, 16))
		return "LUT F Y";
	if (!memcmp(coef, coef_lut_f_c_legacy, 16))
		return "LUT F C";
	return "<UNKNOWN>";
}