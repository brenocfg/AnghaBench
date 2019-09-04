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
struct isac {int (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ISACVer ; 
 int /*<<< orphan*/  ISAC_RBCH ; 
 int stub1 (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isac_version(struct isac *cs)
{
	int val;

	val = cs->read_isac(cs, ISAC_RBCH);
	DBG(1, "ISAC version (%x): %s", val, ISACVer[(val >> 5) & 3]);
}