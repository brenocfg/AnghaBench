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
typedef  struct nfp_mip {scalar_t__* name; } const nfp_mip ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct nfp_mip const*) ; 
 struct nfp_mip const* kmalloc (int,int /*<<< orphan*/ ) ; 
 int nfp_mip_read_resource (struct nfp_cpp*,struct nfp_mip const*) ; 

const struct nfp_mip *nfp_mip_open(struct nfp_cpp *cpp)
{
	struct nfp_mip *mip;
	int err;

	mip = kmalloc(sizeof(*mip), GFP_KERNEL);
	if (!mip)
		return NULL;

	err = nfp_mip_read_resource(cpp, mip);
	if (err) {
		kfree(mip);
		return NULL;
	}

	mip->name[sizeof(mip->name) - 1] = 0;

	return mip;
}