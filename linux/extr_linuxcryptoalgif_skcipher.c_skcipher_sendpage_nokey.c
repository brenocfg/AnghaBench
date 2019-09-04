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
struct socket {int dummy; } ;
struct page {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int af_alg_sendpage (struct socket*,struct page*,int,size_t,int) ; 
 int skcipher_check_key (struct socket*) ; 

__attribute__((used)) static ssize_t skcipher_sendpage_nokey(struct socket *sock, struct page *page,
				       int offset, size_t size, int flags)
{
	int err;

	err = skcipher_check_key(sock);
	if (err)
		return err;

	return af_alg_sendpage(sock, page, offset, size, flags);
}