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
struct sge_fl {int size; int /*<<< orphan*/  desc; int /*<<< orphan*/  cntxt_id; } ;
struct cudbg_qdesc_entry {int qtype; int desc_size; int num_desc; int data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  qid; } ;
typedef  enum cudbg_qdesc_qtype { ____Placeholder_cudbg_qdesc_qtype } cudbg_qdesc_qtype ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void cudbg_fill_qdesc_flq(const struct sge_fl *flq,
					enum cudbg_qdesc_qtype type,
					struct cudbg_qdesc_entry *entry)
{
	entry->qtype = type;
	entry->qid = flq->cntxt_id;
	entry->desc_size = sizeof(__be64);
	entry->num_desc = flq->size;
	entry->data_size = flq->size * sizeof(__be64);
	memcpy(entry->data, flq->desc, entry->data_size);
}