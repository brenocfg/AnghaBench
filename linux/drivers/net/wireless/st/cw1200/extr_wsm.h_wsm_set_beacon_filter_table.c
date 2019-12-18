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
struct wsm_mib_beacon_filter_table {int /*<<< orphan*/  num; } ;
struct wsm_beacon_filter_table_entry {int dummy; } ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  WSM_MIB_ID_BEACON_FILTER_TABLE ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int wsm_write_mib (struct cw1200_common*,int /*<<< orphan*/ ,struct wsm_mib_beacon_filter_table*,size_t) ; 

__attribute__((used)) static inline int wsm_set_beacon_filter_table(struct cw1200_common *priv,
					      struct wsm_mib_beacon_filter_table *ft)
{
	size_t size = __le32_to_cpu(ft->num) *
		     sizeof(struct wsm_beacon_filter_table_entry) +
		     sizeof(__le32);

	return wsm_write_mib(priv, WSM_MIB_ID_BEACON_FILTER_TABLE, ft, size);
}