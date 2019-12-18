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
struct lcs_header {int dummy; } ;
struct lcs_cmd {int offset; scalar_t__ slot; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_q; } ;
struct lcs_card {TYPE_1__ write; } ;
struct lcs_buffer {int count; scalar_t__ data; int /*<<< orphan*/  callback; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_FRAME_TYPE_CONTROL ; 
 struct lcs_buffer* lcs_get_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  lcs_release_buffer ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lcs_buffer *
lcs_get_lancmd(struct lcs_card *card, int count)
{
	struct lcs_buffer *buffer;
	struct lcs_cmd *cmd;

	LCS_DBF_TEXT(4, trace, "getlncmd");
	/* Get buffer and wait if none is available. */
	wait_event(card->write.wait_q,
		   ((buffer = lcs_get_buffer(&card->write)) != NULL));
	count += sizeof(struct lcs_header);
	*(__u16 *)(buffer->data + count) = 0;
	buffer->count = count + sizeof(__u16);
	buffer->callback = lcs_release_buffer;
	cmd = (struct lcs_cmd *) buffer->data;
	cmd->offset = count;
	cmd->type = LCS_FRAME_TYPE_CONTROL;
	cmd->slot = 0;
	return buffer;
}