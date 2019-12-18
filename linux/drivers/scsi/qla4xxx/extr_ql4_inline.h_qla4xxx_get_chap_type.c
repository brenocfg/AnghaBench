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
struct ql4_chap_table {int flags; } ;

/* Variables and functions */
 int BIDI_CHAP ; 
 int BIT_7 ; 
 int LOCAL_CHAP ; 

__attribute__((used)) static inline int qla4xxx_get_chap_type(struct ql4_chap_table *chap_entry)
{
	int type;

	if (chap_entry->flags & BIT_7)
		type = LOCAL_CHAP;
	else
		type = BIDI_CHAP;

	return type;
}