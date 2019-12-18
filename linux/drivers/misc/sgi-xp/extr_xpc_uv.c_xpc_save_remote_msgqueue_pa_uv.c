#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xpc_channel_uv {int /*<<< orphan*/ * cached_notify_gru_mq_desc; } ;
struct TYPE_2__ {struct xpc_channel_uv uv; } ;
struct xpc_channel {TYPE_1__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int /*<<< orphan*/ ) ; 
 int xpc_cache_remote_gru_mq_desc_uv (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static enum xp_retval
xpc_save_remote_msgqueue_pa_uv(struct xpc_channel *ch,
			       unsigned long gru_mq_desc_gpa)
{
	struct xpc_channel_uv *ch_uv = &ch->sn.uv;

	DBUG_ON(ch_uv->cached_notify_gru_mq_desc == NULL);
	return xpc_cache_remote_gru_mq_desc_uv(ch_uv->cached_notify_gru_mq_desc,
					       gru_mq_desc_gpa);
}