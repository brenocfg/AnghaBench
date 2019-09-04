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
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int n2_do_chaining (struct ablkcipher_request*,int) ; 

__attribute__((used)) static int n2_decrypt_chaining(struct ablkcipher_request *req)
{
	return n2_do_chaining(req, false);
}