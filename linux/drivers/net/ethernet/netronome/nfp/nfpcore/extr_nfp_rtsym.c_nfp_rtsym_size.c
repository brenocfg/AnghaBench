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
struct nfp_rtsym {int type; int size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  NFP_RTSYM_TYPE_ABS 131 
#define  NFP_RTSYM_TYPE_FUNCTION 130 
#define  NFP_RTSYM_TYPE_NONE 129 
#define  NFP_RTSYM_TYPE_OBJECT 128 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

u64 nfp_rtsym_size(const struct nfp_rtsym *sym)
{
	switch (sym->type) {
	case NFP_RTSYM_TYPE_NONE:
		pr_err("rtsym '%s': type NONE\n", sym->name);
		return 0;
	default:
		pr_warn("rtsym '%s': unknown type: %d\n", sym->name, sym->type);
		/* fall through */
	case NFP_RTSYM_TYPE_OBJECT:
	case NFP_RTSYM_TYPE_FUNCTION:
		return sym->size;
	case NFP_RTSYM_TYPE_ABS:
		return sizeof(u64);
	}
}