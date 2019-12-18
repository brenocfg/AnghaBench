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
struct scb {int dummy; } ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
ahc_platform_scb_free(struct ahc_softc *ahc, struct scb *scb)
{
}