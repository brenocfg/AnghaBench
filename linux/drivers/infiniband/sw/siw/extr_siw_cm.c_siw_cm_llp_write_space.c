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
struct sock {int dummy; } ;
struct siw_cep {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,int /*<<< orphan*/ ) ; 
 struct siw_cep* sk_to_cep (struct sock*) ; 

__attribute__((used)) static void siw_cm_llp_write_space(struct sock *sk)
{
	struct siw_cep *cep = sk_to_cep(sk);

	if (cep)
		siw_dbg_cep(cep, "state: %d\n", cep->state);
}