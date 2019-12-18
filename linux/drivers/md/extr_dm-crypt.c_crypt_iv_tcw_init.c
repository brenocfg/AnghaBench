#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iv_tcw_private {int /*<<< orphan*/  whitening; int /*<<< orphan*/  iv_seed; } ;
struct TYPE_2__ {struct iv_tcw_private tcw; } ;
struct crypt_config {int key_size; int iv_size; int /*<<< orphan*/ * key; TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int TCW_WHITENING_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int crypt_iv_tcw_init(struct crypt_config *cc)
{
	struct iv_tcw_private *tcw = &cc->iv_gen_private.tcw;
	int key_offset = cc->key_size - cc->iv_size - TCW_WHITENING_SIZE;

	memcpy(tcw->iv_seed, &cc->key[key_offset], cc->iv_size);
	memcpy(tcw->whitening, &cc->key[key_offset + cc->iv_size],
	       TCW_WHITENING_SIZE);

	return 0;
}