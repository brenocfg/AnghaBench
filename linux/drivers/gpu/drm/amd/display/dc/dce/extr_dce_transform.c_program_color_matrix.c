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
struct out_csc_color_matrix {int /*<<< orphan*/ * regval; } ;
struct dce_transform {int dummy; } ;
typedef  enum grph_color_adjust_option { ____Placeholder_grph_color_adjust_option } grph_color_adjust_option ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_CSC_C11 ; 
 int /*<<< orphan*/  OUTPUT_CSC_C11_C12 ; 
 int /*<<< orphan*/  OUTPUT_CSC_C12 ; 
 int /*<<< orphan*/  OUTPUT_CSC_C13_C14 ; 
 int /*<<< orphan*/  OUTPUT_CSC_C21_C22 ; 
 int /*<<< orphan*/  OUTPUT_CSC_C23_C24 ; 
 int /*<<< orphan*/  OUTPUT_CSC_C31_C32 ; 
 int /*<<< orphan*/  OUTPUT_CSC_C33_C34 ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_color_matrix(
	struct dce_transform *xfm_dce,
	const struct out_csc_color_matrix *tbl_entry,
	enum grph_color_adjust_option options)
{
	{
		REG_SET_2(OUTPUT_CSC_C11_C12, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[0],
			OUTPUT_CSC_C12, tbl_entry->regval[1]);
	}
	{
		REG_SET_2(OUTPUT_CSC_C13_C14, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[2],
			OUTPUT_CSC_C12, tbl_entry->regval[3]);
	}
	{
		REG_SET_2(OUTPUT_CSC_C21_C22, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[4],
			OUTPUT_CSC_C12, tbl_entry->regval[5]);
	}
	{
		REG_SET_2(OUTPUT_CSC_C23_C24, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[6],
			OUTPUT_CSC_C12, tbl_entry->regval[7]);
	}
	{
		REG_SET_2(OUTPUT_CSC_C31_C32, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[8],
			OUTPUT_CSC_C12, tbl_entry->regval[9]);
	}
	{
		REG_SET_2(OUTPUT_CSC_C33_C34, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[10],
			OUTPUT_CSC_C12, tbl_entry->regval[11]);
	}
}