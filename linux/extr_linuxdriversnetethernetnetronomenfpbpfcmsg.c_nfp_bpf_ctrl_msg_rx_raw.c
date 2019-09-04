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
struct nfp_app_bpf {int dummy; } ;
struct nfp_app {struct nfp_app_bpf* priv; } ;
struct cmsg_reply_map_simple {int dummy; } ;
struct cmsg_hdr {unsigned int type; } ;

/* Variables and functions */
 unsigned int CMSG_TYPE_BPF_EVENT ; 
 int /*<<< orphan*/  cmsg_warn (struct nfp_app_bpf*,char*,unsigned int) ; 
 int /*<<< orphan*/  nfp_bpf_event_output (struct nfp_app_bpf*,void const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

void
nfp_bpf_ctrl_msg_rx_raw(struct nfp_app *app, const void *data, unsigned int len)
{
	struct nfp_app_bpf *bpf = app->priv;
	const struct cmsg_hdr *hdr = data;

	if (unlikely(len < sizeof(struct cmsg_reply_map_simple))) {
		cmsg_warn(bpf, "cmsg drop - too short %d!\n", len);
		return;
	}

	if (hdr->type == CMSG_TYPE_BPF_EVENT)
		nfp_bpf_event_output(bpf, data, len);
	else
		cmsg_warn(bpf, "cmsg drop - msg type %d with raw buffer!\n",
			  hdr->type);
}