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
struct uclogic_params_frame {int /*<<< orphan*/  desc_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uclogic_params_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uclogic_params_frame_cleanup(struct uclogic_params_frame *frame)
{
	kfree(frame->desc_ptr);
	memset(frame, 0, sizeof(*frame));
}