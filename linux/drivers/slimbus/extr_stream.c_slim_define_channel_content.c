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
typedef  int u8 ;
struct slim_val_inf {int member_1; int* member_3; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_0; } ;
struct slim_stream_runtime {scalar_t__ prot; int bps; struct slim_device* dev; } ;
struct TYPE_2__ {int id; int prrate; int data_fmt; int aux_fmt; int /*<<< orphan*/  state; } ;
struct slim_port {TYPE_1__ ch; } ;
struct slim_device {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SLIM_LDEST_TXN (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct slim_val_inf*) ; 
 int SLIM_CHANNEL_CONTENT_FL ; 
 int /*<<< orphan*/  SLIM_CH_STATE_CONTENT_DEFINED ; 
 int SLIM_MSG_MC_NEXT_DEFINE_CONTENT ; 
 scalar_t__ SLIM_PROTO_ISO ; 
 int SLIM_SLOT_LEN_BITS ; 
 int slim_do_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn ; 

__attribute__((used)) static int slim_define_channel_content(struct slim_stream_runtime *stream,
				       struct slim_port *port)
{
	struct slim_device *sdev = stream->dev;
	u8 wbuf[4];
	struct slim_val_inf msg = {0, 4, NULL, wbuf, NULL};
	u8 mc = SLIM_MSG_MC_NEXT_DEFINE_CONTENT;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 8, stream->dev->laddr, &msg);

	wbuf[0] = port->ch.id;
	wbuf[1] = port->ch.prrate;

	/* Frequency Locked for ISO Protocol */
	if (stream->prot != SLIM_PROTO_ISO)
		wbuf[1] |= SLIM_CHANNEL_CONTENT_FL;

	wbuf[2] = port->ch.data_fmt | (port->ch.aux_fmt << 4);
	wbuf[3] = stream->bps/SLIM_SLOT_LEN_BITS;
	port->ch.state = SLIM_CH_STATE_CONTENT_DEFINED;

	return slim_do_transfer(sdev->ctrl, &txn);
}