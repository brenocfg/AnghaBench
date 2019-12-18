#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long u8 ;
typedef  long long u32 ;
typedef  long long u16 ;
struct mwifiex_private {scalar_t__ adapter; } ;
struct mwifiex_debug_info {int tx_tbl_num; int rx_tbl_num; int tdls_peer_num; TYPE_3__* tdls_list; TYPE_2__* rx_tbl; TYPE_1__* tx_tbl; } ;
struct mwifiex_debug_data {char* name; size_t size; size_t num; size_t addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  peer_addr; } ;
struct TYPE_5__ {int tid; int start_win; int win_size; scalar_t__* buffer; int /*<<< orphan*/  ta; } ;
struct TYPE_4__ {int tid; int /*<<< orphan*/  ra; } ;

/* Variables and functions */
 long get_unaligned (long long*) ; 
 struct mwifiex_debug_data* items ; 
 int num_of_items ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int mwifiex_debug_info_to_buffer(struct mwifiex_private *priv, char *buf,
				 struct mwifiex_debug_info *info)
{
	char *p = buf;
	struct mwifiex_debug_data *d = &items[0];
	size_t size, addr;
	long val;
	int i, j;

	if (!info)
		return 0;

	for (i = 0; i < num_of_items; i++) {
		p += sprintf(p, "%s=", d[i].name);

		size = d[i].size / d[i].num;

		if (i < (num_of_items - 3))
			addr = d[i].addr + (size_t)info;
		else /* The last 3 items are struct mwifiex_adapter variables */
			addr = d[i].addr + (size_t)priv->adapter;

		for (j = 0; j < d[i].num; j++) {
			switch (size) {
			case 1:
				val = *((u8 *)addr);
				break;
			case 2:
				val = get_unaligned((u16 *)addr);
				break;
			case 4:
				val = get_unaligned((u32 *)addr);
				break;
			case 8:
				val = get_unaligned((long long *)addr);
				break;
			default:
				val = -1;
				break;
			}

			p += sprintf(p, "%#lx ", val);
			addr += size;
		}

		p += sprintf(p, "\n");
	}

	if (info->tx_tbl_num) {
		p += sprintf(p, "Tx BA stream table:\n");
		for (i = 0; i < info->tx_tbl_num; i++)
			p += sprintf(p, "tid = %d, ra = %pM\n",
				     info->tx_tbl[i].tid, info->tx_tbl[i].ra);
	}

	if (info->rx_tbl_num) {
		p += sprintf(p, "Rx reorder table:\n");
		for (i = 0; i < info->rx_tbl_num; i++) {
			p += sprintf(p, "tid = %d, ta = %pM, ",
				     info->rx_tbl[i].tid,
				     info->rx_tbl[i].ta);
			p += sprintf(p, "start_win = %d, ",
				     info->rx_tbl[i].start_win);
			p += sprintf(p, "win_size = %d, buffer: ",
				     info->rx_tbl[i].win_size);

			for (j = 0; j < info->rx_tbl[i].win_size; j++)
				p += sprintf(p, "%c ",
					     info->rx_tbl[i].buffer[j] ?
					     '1' : '0');

			p += sprintf(p, "\n");
		}
	}

	if (info->tdls_peer_num) {
		p += sprintf(p, "TDLS peer table:\n");
		for (i = 0; i < info->tdls_peer_num; i++) {
			p += sprintf(p, "peer = %pM",
				     info->tdls_list[i].peer_addr);
			p += sprintf(p, "\n");
		}
	}

	return p - buf;
}