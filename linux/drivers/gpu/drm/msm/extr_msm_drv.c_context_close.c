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
struct msm_file_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct msm_file_private*) ; 
 int /*<<< orphan*/  msm_submitqueue_close (struct msm_file_private*) ; 

__attribute__((used)) static void context_close(struct msm_file_private *ctx)
{
	msm_submitqueue_close(ctx);
	kfree(ctx);
}