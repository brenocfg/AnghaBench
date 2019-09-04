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

/* Variables and functions */
 int CIPHER_BLOCK_SIZE ; 
 int nos_ivs (struct sock*,int) ; 

__attribute__((used)) static int max_ivs_size(struct sock *sk, int size)
{
	return nos_ivs(sk, size) * CIPHER_BLOCK_SIZE;
}