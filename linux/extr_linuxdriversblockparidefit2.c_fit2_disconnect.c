#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  saved_r2; int /*<<< orphan*/  saved_r0; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  w0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fit2_disconnect ( PIA *pi )

{       w0(pi->saved_r0);
        w2(pi->saved_r2);
}