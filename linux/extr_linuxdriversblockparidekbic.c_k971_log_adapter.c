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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  kbic_log_adapter (int /*<<< orphan*/ *,char*,int,char*) ; 

__attribute__((used)) static void k971_log_adapter( PIA *pi, char * scratch, int verbose )

{       kbic_log_adapter(pi,scratch,verbose,"KBIC-971A");
}