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
typedef  int u8 ;
typedef  int u16 ;
struct stmfts_data {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int const STMFTS_MASK_Y_LSB ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmfts_report_hover_event(struct stmfts_data *sdata,
				      const u8 event[])
{
	u16 x = (event[2] << 4) | (event[4] >> 4);
	u16 y = (event[3] << 4) | (event[4] & STMFTS_MASK_Y_LSB);
	u8 z = event[5];

	input_report_abs(sdata->input, ABS_X, x);
	input_report_abs(sdata->input, ABS_Y, y);
	input_report_abs(sdata->input, ABS_DISTANCE, z);

	input_sync(sdata->input);
}