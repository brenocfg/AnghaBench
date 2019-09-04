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
struct si_sm_data {TYPE_1__* io; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* outputb ) (TYPE_1__*,int,unsigned char) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,unsigned char) ; 

__attribute__((used)) static inline void write_smic_control(struct si_sm_data *smic,
				      unsigned char   control)
{
	smic->io->outputb(smic->io, 1, control);
}