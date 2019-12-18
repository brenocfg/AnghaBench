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
typedef  int u16 ;
struct s5c73m3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_SHARPNESS ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s5c73m3_set_sharpness(struct s5c73m3 *state, int val)
{
	u16 reg = (val < 0) ? -val + 2 : val;
	return s5c73m3_isp_command(state, COMM_SHARPNESS, reg);
}