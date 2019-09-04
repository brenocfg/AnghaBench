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
typedef  scalar_t__ u16 ;
struct s5c73m3 {int dummy; } ;

/* Variables and functions */
 scalar_t__ COMM_RESULT_OFFSET ; 
 int s5c73m3_read (struct s5c73m3*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int s5c73m3_isp_comm_result(struct s5c73m3 *state, u16 command,
				   u16 *data)
{
	return s5c73m3_read(state, COMM_RESULT_OFFSET + command, data);
}