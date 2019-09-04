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
struct sii8620_mt_msg {int /*<<< orphan*/  node; } ;
struct sii8620 {int /*<<< orphan*/  mt_queue; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sii8620_mt_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sii8620_mt_msg *sii8620_mt_msg_new(struct sii8620 *ctx)
{
	struct sii8620_mt_msg *msg = kzalloc(sizeof(*msg), GFP_KERNEL);

	if (!msg)
		ctx->error = -ENOMEM;
	else
		list_add_tail(&msg->node, &ctx->mt_queue);

	return msg;
}