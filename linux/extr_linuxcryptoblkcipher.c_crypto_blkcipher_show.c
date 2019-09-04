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
struct seq_file {int dummy; } ;
struct TYPE_2__ {char* min_keysize; char* max_keysize; char* ivsize; scalar_t__ geniv; } ;
struct crypto_alg {char* cra_blocksize; TYPE_1__ cra_blkcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void crypto_blkcipher_show(struct seq_file *m, struct crypto_alg *alg)
{
	seq_printf(m, "type         : blkcipher\n");
	seq_printf(m, "blocksize    : %u\n", alg->cra_blocksize);
	seq_printf(m, "min keysize  : %u\n", alg->cra_blkcipher.min_keysize);
	seq_printf(m, "max keysize  : %u\n", alg->cra_blkcipher.max_keysize);
	seq_printf(m, "ivsize       : %u\n", alg->cra_blkcipher.ivsize);
	seq_printf(m, "geniv        : %s\n", alg->cra_blkcipher.geniv ?:
					     "<default>");
}