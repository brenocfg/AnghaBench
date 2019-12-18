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
struct stm_protocol_driver {int dummy; } ;
struct stm_pdrv_entry {struct config_item_type* node_type; struct stm_protocol_driver* pdrv; } ;
struct config_item_type {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct stm_pdrv_entry* __stm_lookup_protocol (char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stm_get_protocol (struct stm_protocol_driver*) ; 
 int /*<<< orphan*/  stm_pdrv_mutex ; 

int stm_lookup_protocol(const char *name,
			const struct stm_protocol_driver **pdrv,
			const struct config_item_type **node_type)
{
	const struct stm_pdrv_entry *pe;

	mutex_lock(&stm_pdrv_mutex);

	pe = __stm_lookup_protocol(name);
	if (pe && pe->pdrv && stm_get_protocol(pe->pdrv)) {
		*pdrv = pe->pdrv;
		*node_type = pe->node_type;
	}

	mutex_unlock(&stm_pdrv_mutex);

	return pe ? 0 : -ENOENT;
}