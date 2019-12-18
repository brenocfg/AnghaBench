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
typedef  int /*<<< orphan*/  u64 ;
struct rvu {int dummy; } ;
struct nix_lso_format {int offset; int sizem1; int /*<<< orphan*/  alg; void* layer; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIX_AF_LSO_FORMATX_FIELDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIX_LSOALG_ADD_PAYLEN ; 
 int /*<<< orphan*/  NIX_LSOALG_ADD_SEGNUM ; 
 void* NIX_TXLAYER_OL3 ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nix_setup_lso_tso_l3(struct rvu *rvu, int blkaddr,
				 u64 format, bool v4, u64 *fidx)
{
	struct nix_lso_format field = {0};

	/* IP's Length field */
	field.layer = NIX_TXLAYER_OL3;
	/* In ipv4, length field is at offset 2 bytes, for ipv6 it's 4 */
	field.offset = v4 ? 2 : 4;
	field.sizem1 = 1; /* i.e 2 bytes */
	field.alg = NIX_LSOALG_ADD_PAYLEN;
	rvu_write64(rvu, blkaddr,
		    NIX_AF_LSO_FORMATX_FIELDX(format, (*fidx)++),
		    *(u64 *)&field);

	/* No ID field in IPv6 header */
	if (!v4)
		return;

	/* IP's ID field */
	field.layer = NIX_TXLAYER_OL3;
	field.offset = 4;
	field.sizem1 = 1; /* i.e 2 bytes */
	field.alg = NIX_LSOALG_ADD_SEGNUM;
	rvu_write64(rvu, blkaddr,
		    NIX_AF_LSO_FORMATX_FIELDX(format, (*fidx)++),
		    *(u64 *)&field);
}