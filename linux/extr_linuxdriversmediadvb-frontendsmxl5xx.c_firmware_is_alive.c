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
typedef  scalar_t__ u32 ;
struct mxl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HYDRA_HEAR_BEAT ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ read_register (struct mxl*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int firmware_is_alive(struct mxl *state)
{
	u32 hb0, hb1;

	if (read_register(state, HYDRA_HEAR_BEAT, &hb0))
		return 0;
	msleep(20);
	if (read_register(state, HYDRA_HEAR_BEAT, &hb1))
		return 0;
	if (hb1 == hb0)
		return 0;
	return 1;
}