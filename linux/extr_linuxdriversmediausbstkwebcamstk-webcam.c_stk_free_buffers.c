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
struct stk_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stk_clean_iso (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_free_sio_buffers (struct stk_camera*) ; 

__attribute__((used)) static void stk_free_buffers(struct stk_camera *dev)
{
	stk_clean_iso(dev);
	stk_free_sio_buffers(dev);
}