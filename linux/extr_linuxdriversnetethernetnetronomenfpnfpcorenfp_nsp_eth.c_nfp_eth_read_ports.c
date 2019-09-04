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
struct nfp_nsp {int dummy; } ;
struct nfp_eth_table {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 struct nfp_eth_table* __nfp_eth_read_ports (struct nfp_cpp*,struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_close (struct nfp_nsp*) ; 
 struct nfp_nsp* nfp_nsp_open (struct nfp_cpp*) ; 

struct nfp_eth_table *nfp_eth_read_ports(struct nfp_cpp *cpp)
{
	struct nfp_eth_table *ret;
	struct nfp_nsp *nsp;

	nsp = nfp_nsp_open(cpp);
	if (IS_ERR(nsp))
		return NULL;

	ret = __nfp_eth_read_ports(cpp, nsp);
	nfp_nsp_close(nsp);

	return ret;
}