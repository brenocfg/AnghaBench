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
struct falcon_board {scalar_t__ major; int minor; } ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 unsigned int LM87_ALARM_TEMP_EXT1 ; 
 int ef4_check_lm87 (struct ef4_nic*,unsigned int) ; 
 struct falcon_board* falcon_board (struct ef4_nic*) ; 

__attribute__((used)) static int sfe4003_check_hw(struct ef4_nic *efx)
{
	struct falcon_board *board = falcon_board(efx);

	/* A0/A1/A2 board rev. 4003s  report a temperature fault the whole time
	 * (bad sensor) so we mask it out. */
	unsigned alarm_mask =
		(board->major == 0 && board->minor <= 2) ?
		~LM87_ALARM_TEMP_EXT1 : ~0;

	return ef4_check_lm87(efx, alarm_mask);
}