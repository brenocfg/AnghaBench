#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* data; int len; int l2_len; int l4_len; int flag; int /*<<< orphan*/  l3_len; int /*<<< orphan*/  type; void* first; } ;
struct TYPE_3__ {int* data; int len; int /*<<< orphan*/  type; void* first; } ;
union sub_crq {TYPE_2__ hdr; TYPE_1__ hdr_ext; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  hdr_desc ;

/* Variables and functions */
 void* IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  IBMVNIC_HDR_DESC ; 
 int /*<<< orphan*/  IBMVNIC_HDR_EXT_DESC ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (union sub_crq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int create_hdr_descs(u8 hdr_field, u8 *hdr_data, int len, int *hdr_len,
			    union sub_crq *scrq_arr)
{
	union sub_crq hdr_desc;
	int tmp_len = len;
	int num_descs = 0;
	u8 *data, *cur;
	int tmp;

	while (tmp_len > 0) {
		cur = hdr_data + len - tmp_len;

		memset(&hdr_desc, 0, sizeof(hdr_desc));
		if (cur != hdr_data) {
			data = hdr_desc.hdr_ext.data;
			tmp = tmp_len > 29 ? 29 : tmp_len;
			hdr_desc.hdr_ext.first = IBMVNIC_CRQ_CMD;
			hdr_desc.hdr_ext.type = IBMVNIC_HDR_EXT_DESC;
			hdr_desc.hdr_ext.len = tmp;
		} else {
			data = hdr_desc.hdr.data;
			tmp = tmp_len > 24 ? 24 : tmp_len;
			hdr_desc.hdr.first = IBMVNIC_CRQ_CMD;
			hdr_desc.hdr.type = IBMVNIC_HDR_DESC;
			hdr_desc.hdr.len = tmp;
			hdr_desc.hdr.l2_len = (u8)hdr_len[0];
			hdr_desc.hdr.l3_len = cpu_to_be16((u16)hdr_len[1]);
			hdr_desc.hdr.l4_len = (u8)hdr_len[2];
			hdr_desc.hdr.flag = hdr_field << 1;
		}
		memcpy(data, cur, tmp);
		tmp_len -= tmp;
		*scrq_arr = hdr_desc;
		scrq_arr++;
		num_descs++;
	}

	return num_descs;
}