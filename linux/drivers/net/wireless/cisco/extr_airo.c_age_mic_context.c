#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int valid; int window; int /*<<< orphan*/  seed; scalar_t__ tx; scalar_t__ rx; struct TYPE_11__* key; } ;
typedef  TYPE_1__ u8 ;
struct crypto_sync_skcipher {int dummy; } ;
typedef  TYPE_1__ miccntx ;

/* Variables and functions */
 int /*<<< orphan*/  emmh32_setseed (int /*<<< orphan*/ *,TYPE_1__*,int,struct crypto_sync_skcipher*) ; 
 scalar_t__ memcmp (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void age_mic_context(miccntx *cur, miccntx *old, u8 *key, int key_len,
			    struct crypto_sync_skcipher *tfm)
{
	/* If the current MIC context is valid and its key is the same as
	 * the MIC register, there's nothing to do.
	 */
	if (cur->valid && (memcmp(cur->key, key, key_len) == 0))
		return;

	/* Age current mic Context */
	memcpy(old, cur, sizeof(*cur));

	/* Initialize new context */
	memcpy(cur->key, key, key_len);
	cur->window  = 33; /* Window always points to the middle */
	cur->rx      = 0;  /* Rx Sequence numbers */
	cur->tx      = 0;  /* Tx sequence numbers */
	cur->valid   = 1;  /* Key is now valid */

	/* Give key to mic seed */
	emmh32_setseed(&cur->seed, key, key_len, tfm);
}