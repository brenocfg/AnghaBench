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
struct hws_trailer_entry {int dummy; } ;
struct aux_buffer {unsigned long* sdb_index; } ;

/* Variables and functions */
 unsigned long AUX_SDB_INDEX (struct aux_buffer*,unsigned long) ; 
 scalar_t__ trailer_entry_ptr (unsigned long) ; 

__attribute__((used)) static struct hws_trailer_entry *aux_sdb_trailer(struct aux_buffer *aux,
						 unsigned long index)
{
	unsigned long sdb;

	index = AUX_SDB_INDEX(aux, index);
	sdb = aux->sdb_index[index];
	return (struct hws_trailer_entry *)trailer_entry_ptr(sdb);
}