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
typedef  int /*<<< orphan*/  u8 ;
struct ibmvnic_tx_buff {scalar_t__ indir_arr; int /*<<< orphan*/ * hdr_data; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int build_hdr_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ create_hdr_descs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,scalar_t__) ; 

__attribute__((used)) static void build_hdr_descs_arr(struct ibmvnic_tx_buff *txbuff,
				int *num_entries, u8 hdr_field)
{
	int hdr_len[3] = {0, 0, 0};
	int tot_len;
	u8 *hdr_data = txbuff->hdr_data;

	tot_len = build_hdr_data(hdr_field, txbuff->skb, hdr_len,
				 txbuff->hdr_data);
	*num_entries += create_hdr_descs(hdr_field, hdr_data, tot_len, hdr_len,
			 txbuff->indir_arr + 1);
}