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
struct nfp_reprs {unsigned int num_reprs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfp_reprs* kzalloc (int,int /*<<< orphan*/ ) ; 

struct nfp_reprs *nfp_reprs_alloc(unsigned int num_reprs)
{
	struct nfp_reprs *reprs;

	reprs = kzalloc(sizeof(*reprs) +
			num_reprs * sizeof(struct net_device *), GFP_KERNEL);
	if (!reprs)
		return NULL;
	reprs->num_reprs = num_reprs;

	return reprs;
}