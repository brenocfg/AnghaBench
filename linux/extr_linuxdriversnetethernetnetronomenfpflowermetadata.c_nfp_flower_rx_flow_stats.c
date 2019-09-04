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
struct sk_buff {int dummy; } ;
struct nfp_fl_stats_frame {int dummy; } ;
struct nfp_app {int dummy; } ;

/* Variables and functions */
 unsigned char* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 unsigned int nfp_flower_cmsg_get_data_len (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_flower_update_stats (struct nfp_app*,struct nfp_fl_stats_frame*) ; 

void nfp_flower_rx_flow_stats(struct nfp_app *app, struct sk_buff *skb)
{
	unsigned int msg_len = nfp_flower_cmsg_get_data_len(skb);
	struct nfp_fl_stats_frame *stats_frame;
	unsigned char *msg;
	int i;

	msg = nfp_flower_cmsg_get_data(skb);

	stats_frame = (struct nfp_fl_stats_frame *)msg;
	for (i = 0; i < msg_len / sizeof(*stats_frame); i++)
		nfp_flower_update_stats(app, stats_frame + i);
}