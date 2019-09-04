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
struct n2_crypto {int /*<<< orphan*/  cwq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct n2_crypto* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct n2_crypto *alloc_n2cp(void)
{
	struct n2_crypto *np = kzalloc(sizeof(struct n2_crypto), GFP_KERNEL);

	if (np)
		INIT_LIST_HEAD(&np->cwq_list);

	return np;
}