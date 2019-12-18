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
struct amba_id {scalar_t__ data; } ;
struct amba_cs_uci_id {void* data; } ;

/* Variables and functions */

__attribute__((used)) static inline void *coresight_get_uci_data(const struct amba_id *id)
{
	if (id->data)
		return ((struct amba_cs_uci_id *)(id->data))->data;
	return 0;
}