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
struct bus_id_priv {int /*<<< orphan*/  busid_lock; } ;

/* Variables and functions */
 struct bus_id_priv* busid_table ; 
 int /*<<< orphan*/  busid_table_lock ; 
 int get_busid_idx (char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct bus_id_priv *get_busid_priv(const char *busid)
{
	int idx;
	struct bus_id_priv *bid = NULL;

	spin_lock(&busid_table_lock);
	idx = get_busid_idx(busid);
	if (idx >= 0) {
		bid = &(busid_table[idx]);
		/* get busid_lock before returning */
		spin_lock(&bid->busid_lock);
	}
	spin_unlock(&busid_table_lock);

	return bid;
}