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
struct smq_hash_table {int /*<<< orphan*/ * buckets; int /*<<< orphan*/  es; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 struct entry* to_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct entry *h_head(struct smq_hash_table *ht, unsigned bucket)
{
	return to_entry(ht->es, ht->buckets[bucket]);
}