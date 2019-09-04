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
struct xvip_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XVIP_CTRL_CONTROL ; 
 int /*<<< orphan*/  XVIP_CTRL_CONTROL_SW_RESET ; 
 int /*<<< orphan*/  xvip_write (struct xvip_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xvip_reset(struct xvip_device *xvip)
{
	xvip_write(xvip, XVIP_CTRL_CONTROL, XVIP_CTRL_CONTROL_SW_RESET);
}