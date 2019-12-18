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
typedef  int u8 ;
struct nct6683_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCT6683_HWM_CFG ; 
 int nct6683_read (struct nct6683_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct6683_write (struct nct6683_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void nct6683_init_device(struct nct6683_data *data)
{
	u8 tmp;

	/* Start hardware monitoring if needed */
	tmp = nct6683_read(data, NCT6683_HWM_CFG);
	if (!(tmp & 0x80))
		nct6683_write(data, NCT6683_HWM_CFG, tmp | 0x80);
}