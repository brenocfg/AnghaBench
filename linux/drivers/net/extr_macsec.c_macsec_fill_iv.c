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
typedef  int /*<<< orphan*/  u32 ;
struct gcm_iv {int /*<<< orphan*/  pn; int /*<<< orphan*/  sci; } ;
typedef  int /*<<< orphan*/  sci_t ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macsec_fill_iv(unsigned char *iv, sci_t sci, u32 pn)
{
	struct gcm_iv *gcm_iv = (struct gcm_iv *)iv;

	gcm_iv->sci = sci;
	gcm_iv->pn = htonl(pn);
}