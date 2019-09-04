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
typedef  int float32 ;
typedef  int flag ;
typedef  scalar_t__ bits32 ;

/* Variables and functions */
 int extractFloat32Exp (int) ; 
 scalar_t__ extractFloat32Frac (int) ; 
 int extractFloat32Sign (int) ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  float_raise (int /*<<< orphan*/ ) ; 

flag float32_lt( float32 a, float32 b )
{
    flag aSign, bSign;

    if (    ( ( extractFloat32Exp( a ) == 0xFF ) && extractFloat32Frac( a ) )
         || ( ( extractFloat32Exp( b ) == 0xFF ) && extractFloat32Frac( b ) )
       ) {
        float_raise( float_flag_invalid );
        return 0;
    }
    aSign = extractFloat32Sign( a );
    bSign = extractFloat32Sign( b );
    if ( aSign != bSign ) return aSign && ( (bits32) ( ( a | b )<<1 ) != 0 );
    return ( a != b ) && ( aSign ^ ( a < b ) );

}