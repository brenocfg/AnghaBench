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
typedef  int u64 ;
struct niu_tcam_entry {int assoc_data; int valid; void** key_mask; void** key; } ;
struct niu_parent {struct niu_tcam_entry* tcam; } ;
struct niu_classifier {int tcam_top; int /*<<< orphan*/  tcam_valid_entries; } ;
struct niu {struct niu_classifier clas; struct niu_parent* parent; } ;

/* Variables and functions */
 int TCAM_ASSOCDATA_OFFSET_SHIFT ; 
 int TCAM_ASSOCDATA_TRES_USE_OFFSET ; 
 void* TCAM_V4KEY1_NOPORT ; 
 int /*<<< orphan*/  memset (struct niu_tcam_entry*,int /*<<< orphan*/ ,int) ; 
 int tcam_assoc_write (struct niu*,int,int) ; 
 int tcam_write (struct niu*,int,void**,void**) ; 

__attribute__((used)) static int niu_set_ip_frag_rule(struct niu *np)
{
	struct niu_parent *parent = np->parent;
	struct niu_classifier *cp = &np->clas;
	struct niu_tcam_entry *tp;
	int index, err;

	index = cp->tcam_top;
	tp = &parent->tcam[index];

	/* Note that the noport bit is the same in both ipv4 and
	 * ipv6 format TCAM entries.
	 */
	memset(tp, 0, sizeof(*tp));
	tp->key[1] = TCAM_V4KEY1_NOPORT;
	tp->key_mask[1] = TCAM_V4KEY1_NOPORT;
	tp->assoc_data = (TCAM_ASSOCDATA_TRES_USE_OFFSET |
			  ((u64)0 << TCAM_ASSOCDATA_OFFSET_SHIFT));
	err = tcam_write(np, index, tp->key, tp->key_mask);
	if (err)
		return err;
	err = tcam_assoc_write(np, index, tp->assoc_data);
	if (err)
		return err;
	tp->valid = 1;
	cp->tcam_valid_entries++;

	return 0;
}