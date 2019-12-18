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
struct sock {int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_err; } ;
struct siw_cep {int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct siw_cep* sk_to_cep (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void siw_cm_llp_error_report(struct sock *sk)
{
	struct siw_cep *cep = sk_to_cep(sk);

	if (cep) {
		siw_dbg_cep(cep, "error %d, socket state: %d, cep state: %d\n",
			    sk->sk_err, sk->sk_state, cep->state);
		cep->sk_error_report(sk);
	}
}