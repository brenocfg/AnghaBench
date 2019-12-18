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
typedef  int u8 ;
typedef  int u32 ;
struct list_head {int dummy; } ;
struct bfa_s {int dummy; } ;
struct bfa_fcxp_s {int /*<<< orphan*/  fcxp_tag; } ;
typedef  int /*<<< orphan*/ ** bfa_fcxp_get_sglen_t ;
typedef  int /*<<< orphan*/ ** bfa_fcxp_get_sgaddr_t ;

/* Variables and functions */
 int BFI_SGE_INLINE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcxp_init_reqrsp(struct bfa_fcxp_s *fcxp,
	       struct bfa_s *bfa,
	       u8 *use_ibuf,
	       u32 *nr_sgles,
	       bfa_fcxp_get_sgaddr_t *r_sga_cbfn,
	       bfa_fcxp_get_sglen_t *r_sglen_cbfn,
	       struct list_head *r_sgpg_q,
	       int n_sgles,
	       bfa_fcxp_get_sgaddr_t sga_cbfn,
	       bfa_fcxp_get_sglen_t sglen_cbfn)
{

	WARN_ON(bfa == NULL);

	bfa_trc(bfa, fcxp->fcxp_tag);

	if (n_sgles == 0) {
		*use_ibuf = 1;
	} else {
		WARN_ON(*sga_cbfn == NULL);
		WARN_ON(*sglen_cbfn == NULL);

		*use_ibuf = 0;
		*r_sga_cbfn = sga_cbfn;
		*r_sglen_cbfn = sglen_cbfn;

		*nr_sgles = n_sgles;

		/*
		 * alloc required sgpgs
		 */
		if (n_sgles > BFI_SGE_INLINE)
			WARN_ON(1);
	}

}