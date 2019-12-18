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
struct nfp_rtsym_table {int dummy; } ;
struct nfp_mip {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 struct nfp_rtsym_table* __nfp_rtsym_table_read (struct nfp_cpp*,struct nfp_mip const*) ; 
 int /*<<< orphan*/  nfp_mip_close (struct nfp_mip const*) ; 
 struct nfp_mip* nfp_mip_open (struct nfp_cpp*) ; 

struct nfp_rtsym_table *nfp_rtsym_table_read(struct nfp_cpp *cpp)
{
	struct nfp_rtsym_table *rtbl;
	const struct nfp_mip *mip;

	mip = nfp_mip_open(cpp);
	rtbl = __nfp_rtsym_table_read(cpp, mip);
	nfp_mip_close(mip);

	return rtbl;
}