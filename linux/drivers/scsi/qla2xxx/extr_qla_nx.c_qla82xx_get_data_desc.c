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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qla_hw_data {size_t file_prd_off; TYPE_2__* hablob; } ;
struct qla82xx_uri_table_desc {int findex; int entry_size; } ;
struct qla82xx_uri_data_desc {int dummy; } ;
typedef  size_t __le32 ;
struct TYPE_4__ {TYPE_1__* fw; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 
 struct qla82xx_uri_table_desc* qla82xx_get_table_desc (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static struct qla82xx_uri_data_desc *
qla82xx_get_data_desc(struct qla_hw_data *ha,
	u32 section, u32 idx_offset)
{
	const u8 *unirom = ha->hablob->fw->data;
	int idx = cpu_to_le32(*((int *)&unirom[ha->file_prd_off] + idx_offset));
	struct qla82xx_uri_table_desc *tab_desc = NULL;
	__le32 offset;

	tab_desc = qla82xx_get_table_desc(unirom, section);
	if (!tab_desc)
		return NULL;

	offset = cpu_to_le32(tab_desc->findex) +
	    (cpu_to_le32(tab_desc->entry_size) * idx);

	return (struct qla82xx_uri_data_desc *)&unirom[offset];
}