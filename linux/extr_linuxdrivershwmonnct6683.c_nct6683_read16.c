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
typedef  int u16 ;
struct nct6683_data {int dummy; } ;

/* Variables and functions */
 int nct6683_read (struct nct6683_data*,int) ; 

__attribute__((used)) static u16 nct6683_read16(struct nct6683_data *data, u16 reg)
{
	return (nct6683_read(data, reg) << 8) | nct6683_read(data, reg + 1);
}