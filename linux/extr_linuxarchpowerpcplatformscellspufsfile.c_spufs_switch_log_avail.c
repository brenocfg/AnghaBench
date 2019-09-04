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
struct spu_context {int dummy; } ;

/* Variables and functions */
 int SWITCH_LOG_BUFSIZE ; 
 int spufs_switch_log_used (struct spu_context*) ; 

__attribute__((used)) static inline int spufs_switch_log_avail(struct spu_context *ctx)
{
	return SWITCH_LOG_BUFSIZE - spufs_switch_log_used(ctx);
}