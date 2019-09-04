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
typedef  enum rdma_ch_state { ____Placeholder_rdma_ch_state } rdma_ch_state ;

/* Variables and functions */
#define  CH_CONNECTING 132 
#define  CH_DISCONNECTED 131 
#define  CH_DISCONNECTING 130 
#define  CH_DRAINING 129 
#define  CH_LIVE 128 

__attribute__((used)) static const char *get_ch_state_name(enum rdma_ch_state s)
{
	switch (s) {
	case CH_CONNECTING:
		return "connecting";
	case CH_LIVE:
		return "live";
	case CH_DISCONNECTING:
		return "disconnecting";
	case CH_DRAINING:
		return "draining";
	case CH_DISCONNECTED:
		return "disconnected";
	}
	return "???";
}