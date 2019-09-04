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
typedef  int u32 ;
struct mc5 {unsigned char mode; unsigned char part_type; unsigned int tcam_size; struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MC5_DB_CONFIG ; 
 int F_TMTYPEHI ; 
 size_t G_TMPARTSIZE (int) ; 
 scalar_t__ G_TMTYPE (int) ; 
 int MC5_MODE_144_BIT ; 
 int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

void t3_mc5_prep(struct adapter *adapter, struct mc5 *mc5, int mode)
{
#define K * 1024

	static unsigned int tcam_part_size[] = {	/* in K 72-bit entries */
		64 K, 128 K, 256 K, 32 K
	};

#undef K

	u32 cfg = t3_read_reg(adapter, A_MC5_DB_CONFIG);

	mc5->adapter = adapter;
	mc5->mode = (unsigned char)mode;
	mc5->part_type = (unsigned char)G_TMTYPE(cfg);
	if (cfg & F_TMTYPEHI)
		mc5->part_type |= 4;

	mc5->tcam_size = tcam_part_size[G_TMPARTSIZE(cfg)];
	if (mode == MC5_MODE_144_BIT)
		mc5->tcam_size /= 2;
}