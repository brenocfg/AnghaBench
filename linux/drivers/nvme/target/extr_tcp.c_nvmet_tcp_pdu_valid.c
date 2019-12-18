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
typedef  int u8 ;

/* Variables and functions */
#define  nvme_tcp_cmd 130 
#define  nvme_tcp_h2c_data 129 
#define  nvme_tcp_icreq 128 

__attribute__((used)) static inline bool nvmet_tcp_pdu_valid(u8 type)
{
	switch (type) {
	case nvme_tcp_icreq:
	case nvme_tcp_cmd:
	case nvme_tcp_h2c_data:
		/* fallthru */
		return true;
	}

	return false;
}