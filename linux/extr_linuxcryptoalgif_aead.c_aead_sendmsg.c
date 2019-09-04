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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct msghdr {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct alg_sock {struct aead_tfm* private; struct sock* parent; } ;
struct aead_tfm {struct crypto_aead* aead; } ;

/* Variables and functions */
 int af_alg_sendmsg (struct socket*,struct msghdr*,size_t,unsigned int) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 

__attribute__((used)) static int aead_sendmsg(struct socket *sock, struct msghdr *msg, size_t size)
{
	struct sock *sk = sock->sk;
	struct alg_sock *ask = alg_sk(sk);
	struct sock *psk = ask->parent;
	struct alg_sock *pask = alg_sk(psk);
	struct aead_tfm *aeadc = pask->private;
	struct crypto_aead *tfm = aeadc->aead;
	unsigned int ivsize = crypto_aead_ivsize(tfm);

	return af_alg_sendmsg(sock, msg, size, ivsize);
}